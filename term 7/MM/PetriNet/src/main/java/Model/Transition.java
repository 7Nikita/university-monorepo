package Model;

import lombok.Getter;

import java.util.ArrayList;
import java.util.List;

public class Transition extends PetriNetObject {

    @Getter private List<Arc> incoming = new ArrayList<>();
    @Getter private List<Arc> outgoing = new ArrayList<>();

    public Transition(String name) {
        super(name);
    }

    public boolean canFire() {
        boolean canFire = true;
        for (Arc arc: incoming) {
            canFire &= arc.canFire();
        }
        for (Arc arc: outgoing) {
            canFire &= arc.canFire();
        }
        return canFire;
    }

    public void fire() {
        for (Arc arc: incoming) {
            arc.fire();
        }

        for (Arc arc: outgoing) {
            arc.fire();
        }
    }

    public void addIncoming(Arc arc) { incoming.add(arc); }

    public void addOutgoing(Arc arc) { outgoing.add(arc); }
}
