import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.Base64;

/**
 * Bounded regression check for the AVX-512 Base64 decoder tail.
 * Run on a disposable x86-64 host with AVX-512 VBMI after installing a
 * patched JDK. A pass on a host without those CPU features is inconclusive.
 */
public final class Base64TailCheck {
    private static volatile int sink;

    public static void main(String[] args) {
        int major = Runtime.version().feature();
        if (major < 17) {
            throw new IllegalArgumentException("Expected JDK 17 or newer: " + major);
        }

        int blockLength = major == 17 ? 128 : 64;
        byte[] valid = "A".repeat(blockLength).getBytes(StandardCharsets.US_ASCII);
        byte[] malformed = ("A".repeat(blockLength) + "=")
                .getBytes(StandardCharsets.US_ASCII);
        byte[] output = new byte[4096];
        Base64.Decoder decoder = Base64.getDecoder();

        for (int i = 0; i < 200_000; i++) {
            sink += decoder.decode(valid, output);
        }

        Arrays.fill(output, (byte) 0x5a);
        boolean rejected = false;
        try {
            decoder.decode(malformed, output);
        } catch (IllegalArgumentException expected) {
            rejected = true;
        }

        int decodedLength = 3 * ((malformed.length + 3) / 4) - 1;
        int changed = 0;
        for (int i = decodedLength; i < output.length; i++) {
            if (output[i] != (byte) 0x5a) {
                changed++;
            }
        }

        System.out.printf("JDK %s: rejected=%s bytesChangedPastOutput=%d%n",
                System.getProperty("java.runtime.version"), rejected, changed);
        if (!rejected || changed != 0) {
            throw new AssertionError("Base64 tail wrote past its output");
        }
    }
}
