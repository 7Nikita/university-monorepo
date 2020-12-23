package Model;

import lombok.Getter;


public class Arc  extends PetriNetObject {

    @Getter Place place;
    @Getter Transition transition;
    @Getter Direction direction;

    int weight = 1;

    public Arc(String name, Direction d, Place p, Transition t) {
        super(name);
        this.place = p;
        this.transition = t;
        this.direction = d;
    }

    public Arc(String name, Place p, Transition t) {
        this(name, Direction.PLACE_TO_TRANSITION, p, t);
        t.addIncoming(this);
    }

    public Arc(String name, Transition t, Place p) {
        this(name, Direction.TRANSITION_TO_PLACE, p, t);
        t.addOutgoing(this);
    }

    public boolean canFire() { return direction.canFire(place, weight); }

    public void fire() { direction.fire(place, weight); }

}
