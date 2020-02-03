public class Caesar extends Cipher {

    private final int shift;

    public Caesar(String alphabet, int shift) {
        super(alphabet);
        this.shift = shift;
    }

    @Override
    public String decode(String text) {
        StringBuilder out = new StringBuilder();

        for (int i = 0; i < text.length(); ++i) {
            final Character element = text.charAt(i);
            if (!isInAlphabet(element)) {
                out.append(element);
                continue;
            }
            out.append(characterOf(boundedIndexOf(indexOf(element) - shift)));
        }

        return out.toString();
    }

    @Override
    public String encode(String text) {
        StringBuilder out = new StringBuilder();

        for (int i = 0; i < text.length(); ++i) {
            final Character element = text.charAt(i);
            if (!isInAlphabet(element)) {
                out.append(element);
                continue;
            }
            out.append(characterOf(boundedIndexOf(indexOf(element) + shift)));
        }

        return out.toString();
    }
}
