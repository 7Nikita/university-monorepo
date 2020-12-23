package Model;

import lombok.Getter;
import lombok.Setter;

public class Place extends PetriNetObject {

    @Getter @Setter private int tokens = 0;

    public Place(String name, int val) {
        super(name);
        this.setTokens(val);
    }

    public void addTokens(int cnt) { this.tokens += cnt; }

    public void removeTokens(int cnt) { this.tokens -= cnt; }

    public boolean isEnoughTokens(int threshold) { return (tokens >= threshold); }

}
