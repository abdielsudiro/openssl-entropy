# OpenSSL-entropy

Own lab to proof how RAND_bytes() work.

The code that includes a call to `RAND_add` with hard-coded entropy sources: a timestamp (in microseconds), the process ID (`PID`), and a simulated "mouse movement" value. These values are then fed into `RAND_add` to strengthen the entropy before calling `RAND_bytes`.
