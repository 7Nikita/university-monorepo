import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class CaesarTest {

    @Test
    public void testCaesarCipherEncode() {
        Cipher cipher = new Caesar("abcd34", 4);
        assertEquals(cipher.encode("ascd43"), "3sabdc");
    }

    @Test
    public void testCaesarCipherDecode() {
        Cipher cipher = new Caesar("abcd34", 4);
        assertEquals(cipher.decode("cs34ba"), "3sabdc");
    }

}
