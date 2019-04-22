import java.util.Base64;
import java.security.PrivateKey;

public class Main {
  public static void main(String[] args) {
    final PrivateKey generatePrivate = null;

    final byte[] encoded = Base64.getEncoder().encode(generatePrivate.getEncoded());

    System.out.printf("key format: %s\n", generatePrivate.getFormat());
    System.out.println(new String(encoded));
  }
}

