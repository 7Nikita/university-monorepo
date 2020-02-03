public class Vigenere extends Cipher {

    private final String keyword;

    public Vigenere(String alphabet, String keyword) {
        super(alphabet);

        for (int i = 0; i < keyword.length(); ++i) {
            final Character element = keyword.charAt(i);
            if (!isInAlphabet(element)) {
                throw new IllegalArgumentException();
            }
        }

        this.keyword = keyword;
    }

    @Override
    String decode(String text) {
        StringBuilder out = new StringBuilder();
        int kw_index = 0;

        for (int i = 0; i < text.length(); ++i) {
            final Character element = text.charAt(i);

            if (!isInAlphabet(element)) {
                out.append(element);
                continue;
            }

            final int m = indexOf(element);
            final int k = indexOf(keyword.charAt(kw_index));

            out.append(characterOf(boundedIndexOf(m - k)));

            ++kw_index;
            if (kw_index == keyword.length()) {
                kw_index = 0;
            }
        }

        return out.toString();
    }

    @Override
    String encode(String text) {
        StringBuilder out = new StringBuilder();
        int kw_index = 0;

        for (int i = 0; i < text.length(); ++i) {
            final Character element = text.charAt(i);

            if (!isInAlphabet(element)) {
                out.append(element);
                continue;
            }

            final int m = indexOf(element);
            final int k = indexOf(keyword.charAt(kw_index));

            out.append(characterOf(boundedIndexOf(m + k)));

            ++kw_index;
            if (kw_index == keyword.length()) {
                kw_index = 0;
            }
        }

        return out.toString();
    }
}
