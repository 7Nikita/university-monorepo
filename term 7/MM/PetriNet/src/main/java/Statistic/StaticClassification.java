package Statistic;

import Model.*;

import java.util.*;

import com.google.common.collect.HashMultimap;
import com.google.common.collect.ListMultimap;
import com.google.common.collect.ArrayListMultimap;
import com.google.common.collect.SetMultimap;

import static Model.Direction.PLACE_TO_TRANSITION;

public class StaticClassification {

    final PetriNet net;

    public StaticClassification(PetriNet net) { this.net = net; }

    public boolean isFreeChoice() {
        SetMultimap<String, String> transitionsForPlace = HashMultimap.create();
        SetMultimap<String, String> placesForTransition = HashMultimap.create();
        for (Arc a: net.getArcs()) {
            String placeName = a.getPlace().getName();
            if (a.getDirection() == PLACE_TO_TRANSITION) {
                transitionsForPlace.put(placeName, a.getTransition().getName());
                placesForTransition.put(a.getTransition().getName(), placeName);
            }
        }
        for (String placeName: transitionsForPlace.keys()) {
            Set<String> transitions = transitionsForPlace.get(placeName);
            if (transitions.size() > 1) {
                for (String transitionName : transitions) {
                    if (placesForTransition.get(transitionName).size() > 1) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    public boolean isMarkedGraph() {
        Map<String, Integer> in = new HashMap<>();
        Map<String, Integer> out = new HashMap<>();
        for (Arc a: net.getArcs()) {
            String placeName = a.getPlace().getName();
            if (a.getDirection() == PLACE_TO_TRANSITION)  {
                in.merge(placeName, 1, Integer::sum);
            } else {
                out.merge(placeName, 1, Integer::sum);
            }
        }
        for (Place p: net.getPlaces()) {
            String placeName = p.getName();
            if (in.get(placeName) != 1) {
                return false;
            }
            if (out.get(placeName) != 1) {
                return false;
            }
        }
        return true;
    }

    public boolean isAutomatic() {
        boolean flag = true;
        for (Transition t: net.getTransitions()) {
            flag &= ((t.getIncoming().size() <= 1) && (t.getOutgoing().size() <= 1));
        }
        return flag;
    }

    public boolean isConflict() {
        ListMultimap<String, String> in = ArrayListMultimap.create();
        ListMultimap<String, String> out = ArrayListMultimap.create();
        for (Arc a: net.getArcs()) {
            String placeName = a.getPlace().getName();
            if (a.getDirection() == PLACE_TO_TRANSITION) {
                in.put(placeName, a.getName());
            } else {
                out.put(placeName, a.getName());
            }
        }
        for (Place p: net.getPlaces()) {
            String placeName = p.getName();
            List<String> inArcs = in.get(placeName);
            if (inArcs.size() <= 1) {
                continue;
            }
            List<String> outArcs = out.get(placeName);
            if (!outArcs.equals(inArcs)) {
                return true;
            }
        }
        return false;
    }

}
