import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public abstract class Cipher {

    private List<Character> alphabet = new LinkedList<>();
    private Map<Character, Integer> charPosition = new HashMap<>();

    public Cipher(final String alphabet) {
        int index = 0;
        for (int i = 0; i < alphabet.length(); ++i) {
            Character element = alphabet.charAt(i);
            if (!isInAlphabet(element)) {
                this.alphabet.add(element);
                this.charPosition.put(element, index++);
            }
        }
    }

    public boolean isInAlphabet(Character c) {
        return alphabet.contains(c);
    }

    public int indexOf(Character c) {
        return charPosition.get(c);
    }

    public int boundedIndexOf(int unboundedIndex) {
        unboundedIndex %= alphabet.size();
        if (unboundedIndex < 0) {
            unboundedIndex += alphabet.size();
        }
        return unboundedIndex;
    }

    public char characterOf(int pos) {
        return alphabet.get(pos);
    }

    abstract String decode(final String text);
    abstract String encode(final String text);

}
