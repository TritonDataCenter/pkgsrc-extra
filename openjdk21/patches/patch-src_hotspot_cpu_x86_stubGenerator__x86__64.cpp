$NetBSD$

Avoid an out-of-bounds write in the AVX-512 Base64 decoder when a
malformed padded tail has fewer than four bytes (CVE-2026-114938).
Backport of OpenJDK JDK-8393212:
https://github.com/openjdk/jdk21u/commit/8e115fb5c7c5e2b35f0aa86353ce3f84b49e7319

--- src/hotspot/cpu/x86/stubGenerator_x86_64.cpp.orig
+++ src/hotspot/cpu/x86/stubGenerator_x86_64.cpp
@@ -2534,6 +2534,10 @@ address StubGenerator::generate_base64_decodeBlock() {
     __ BIND(L_finalBit);
     // Now have 1 to 63 bytes left to decode
-
+
+    // A padded Base64 tail shorter than one complete block is handled by Java.
+    __ cmpl(length, 4);
+    __ jcc(Assembler::less, L_bruteForce);
+
     // I was going to let Java take care of the final fragment
     // however it will repeatedly call this routine for every 4 bytes
     // of input data, so handle the rest here.
