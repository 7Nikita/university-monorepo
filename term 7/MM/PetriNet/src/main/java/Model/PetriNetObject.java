package Model;

import lombok.Getter;
import lombok.Setter;


public class PetriNetObject {

    @Getter @Setter private String name;

    public PetriNetObject(String name) {
        this.name = name;
    }

}
