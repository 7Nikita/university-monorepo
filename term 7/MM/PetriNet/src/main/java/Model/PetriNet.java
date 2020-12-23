package Model;

import lombok.Getter;
import lombok.Setter;

import java.util.ArrayList;
import java.util.List;

public class PetriNet {

    @Getter private List<Arc> arcs = new ArrayList<>();
    @Getter private List<Place> places = new ArrayList<>();
    @Getter @Setter private List<Transition> transitions = new ArrayList<>();

    public void add(PetriNetObject o) {
        if (o instanceof Arc) {
            arcs.add((Arc) o);
        } else if (o instanceof Place) {
            places.add((Place) o);
        } else if (o instanceof Transition) {
            transitions.add((Transition) o);
        }
    }

    public List<Transition> getTransitionsAbleToFire() {
        List<Transition> list = new ArrayList<Transition>();
        for (Transition t: transitions) {
            if (t.canFire()) {
                list.add(t);
            }
        }
        return list;
    }

    public Transition transition(String name) {
        Transition t = new Transition(name);
        transitions.add(t);
        return t;
    }

    public Place place(String name) {
        return this.place(name, 0);
    }

    public Place place(String name, int val) {
        Place p = new Place(name, val);
        places.add(p);
        return p;
    }

    public Arc arc(String name, Place p, Transition t) {
        Arc arc = new Arc(name, p, t);
        arcs.add(arc);
        return arc;
    }

    public Arc arc(String name, Transition t, Place p) {
        Arc arc = new Arc(name, t, p);
        arcs.add(arc);
        return arc;
    }

//    @Override
//    public Object clone() throws CloneNotSupportedException {
//        return super.clone();
//    }

}
