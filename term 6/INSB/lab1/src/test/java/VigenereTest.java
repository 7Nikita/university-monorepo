import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class VigenereTest {

    @Test
    public void testVigenereEncode() {
        Cipher cipher = new Vigenere("abcdek", "abdek");
        assertEquals(cipher.encode("afs21h"), "afs21h");
    }

    @Test
    public void testVigenereDecode() {
        Cipher cipher = new Vigenere("abcdek", "abdek");
        assertEquals(cipher.decode("afs21h"), "afs21h");

    }

}
