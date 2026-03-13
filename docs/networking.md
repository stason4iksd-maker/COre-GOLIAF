# Networking Security & Transport Design

## Security baseline

- **XOR-based obfuscation is explicitly prohibited** for payload protection. XOR does not provide semantic security, is trivially reversible under known-plaintext conditions, and must not be presented as cryptography.
- Use standard, modern cryptography (for example, AEAD ciphers such as AES-GCM or ChaCha20-Poly1305) for confidentiality + integrity where encryption is required.

## Connection bootstrap: challenge-response handshake

A connection MUST complete a challenge-response handshake before accepting gameplay/application traffic.

### Handshake flow

1. **ClientHello**
   - Includes: protocol version, client random, timestamp, and requested auth mode.
2. **ServerChallenge**
   - Includes: server random, challenge nonce, server timestamp, and optional salt/id.
3. **ClientResponse**
   - Includes: proof computed over handshake transcript (e.g., HMAC/KDF-based response), challenge nonce echo, and client capabilities.
4. **ServerAccept / ServerReject**
   - Server verifies proof, freshness, and anti-replay windows.

### Replay protection requirements

For every accepted session:

- Assign a **session ID** and maintain a **monotonic sequence number** per direction.
- Reject packets with:
  - duplicate `(session_id, sequence_number)`;
  - sequence numbers lower than the accepted window lower-bound;
  - missing/invalid nonce binding.
- Bind packet authentication to `{session_id, sequence_number, nonce, channel_id}`.
- Nonce policy:
  - unique per protected packet under a given key;
  - never reused after reconnect/key rotation;
  - enforce strict monotonicity or sliding-window uniqueness checks.

## Optional server password and packet rate limiting

### Optional `server password`

If configured, server password is required during handshake (never in plaintext logs):

- Derive proof from password using a KDF/HMAC strategy with server-provided salt/challenge.
- Compare in constant time.
- Do not expose whether username/server exists vs wrong password in externally visible errors.

### Packet rate limit

Rate limiting is mandatory for handshake and runtime packet processing:

- Per-IP + per-session token bucket (or equivalent).
- Distinct limits for:
  - handshake packets;
  - reliable events;
  - unreliable snapshots.
- Exceeding limit actions:
  - soft drop for burst overflow;
  - temporary cooldown/ban for sustained abuse.
- Record metrics (drops, bans, top talkers) for operational visibility.

## ENet channel separation and payload limits

Use dedicated ENet channels by traffic class:

1. **Channel 0: Reliable Events**
   - ENet reliable flag enabled.
   - For critical gameplay/control events.
2. **Channel 1: Unreliable Snapshots**
   - ENet unreliable/unsequenced mode as appropriate.
   - For frequent state snapshots where newest data supersedes old.

### Size limits (hard caps)

Define and enforce caps before serialization send:

- `reliable_event_max_bytes`: e.g., 4-8 KB.
- `snapshot_max_bytes`: e.g., 512-1400 B (fit MTU strategy).
- `handshake_packet_max_bytes`: small fixed cap (e.g., <= 1 KB).

Server MUST drop and log oversize packets and increment abuse counters.

## Threat model

### In-scope attacks and countermeasures

1. **Replay attacks**
   - Attack: captured valid packets resent later.
   - Countermeasures: challenge-response, nonce uniqueness, sequence windows, session binding.

2. **Packet forgery / tampering**
   - Attack: attacker modifies or fabricates payloads.
   - Countermeasures: authenticated encryption or per-packet MAC over header + payload metadata.

3. **Brute-force against optional server password**
   - Attack: repeated password guesses.
   - Countermeasures: handshake rate limits, cooldown/ban, KDF-based proof, generic auth failures.

4. **Flood / DoS via packet storms**
   - Attack: overwhelm server with handshake or data packets.
   - Countermeasures: per-IP/session rate limits, hard size caps, early packet validation + drop.

5. **Channel starvation / HOL effects misuse**
   - Attack: abuse reliable channel to delay critical traffic.
   - Countermeasures: split reliable vs unreliable channels, queue caps, priority scheduling.

6. **Protocol downgrade / incompatible client abuse**
   - Attack: force weaker behavior through version confusion.
   - Countermeasures: strict version negotiation, reject unknown/legacy insecure modes.

### Out-of-scope assumptions (explicit)

- Endpoint compromise (malware/root on client/server host).
- L3/L4 volumetric DDoS beyond edge/network provider capacity.
- Physical access attacks against server hardware.

## Implementation checklist

- [ ] Remove any mention/usage of XOR as cryptography.
- [ ] Implement challenge-response handshake gates before gameplay packets.
- [ ] Enforce nonce + sequence anti-replay validation.
- [ ] Add optional `server password` flow in handshake.
- [ ] Add per-IP and per-session rate limits.
- [ ] Split ENet channels for reliable events vs unreliable snapshots.
- [ ] Enforce payload size caps per packet class.
- [ ] Add metrics/logging for drops, replays, and auth failures.
