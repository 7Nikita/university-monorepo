package Statistic;

import Model.PetriNet;
import Model.Place;
import Model.Transition;
import lombok.Getter;

import java.util.*;

public class DynamicClassification {

    final private PetriNet net;
    final private List<Integer> initialMarking;
    @Getter private Set<List<Integer>> markings = new HashSet<>();

    public DynamicClassification(PetriNet net) {
        this.net = net;
        initialMarking = getMarking();
        calculate();
    }

    // Characteristics
    @Getter private Set<List<Integer>> possibleMarkings;
    @Getter private int kLimitation;
    @Getter private boolean safety;
    @Getter private boolean conservativeness;
    @Getter private boolean parallelness;
    @Getter private boolean liveness = true;
    @Getter private boolean stability = true;


    void calculate() {
        getPaths();
        possibleMarkings = Set.copyOf(markings);
        resetNet();
        kLimitation = kLimited();
        safety = isSafe();
        conservativeness = isConservative();
        resetNet();
        resetMarkings();
        parallelness = hasParallelTransitions();
        resetNet();
        resetMarkings();
        isLive();
        resetNet();
        resetMarkings();
        isStable();
        resetNet();
        resetMarkings();
    }

    private void resetNet() {
        List<Place> places = net.getPlaces();
        for (int i = 0; i < initialMarking.size(); ++i) {
            places.get(i).setTokens(initialMarking.get(i));
        }
    }

    private void resetMarkings() {
        markings.clear();
    }

    private void getPaths() {
        List<Integer> curMarking = getMarking();
        if (markings.contains(curMarking)) {
            return;
        }
        markings.add(curMarking);
        for (Transition t: net.getTransitionsAbleToFire()) {
            // PetriNet copy = (PetriNet) curNet.clone();
            t.fire();
            getPaths();
            // curNet = copy;
            List<Place> places = net.getPlaces();
            for (int i = 0; i < curMarking.size(); ++i) {
                places.get(i).setTokens(curMarking.get(i));
            }
        }
    }

    private boolean hasParallelTransitions() {
        List<Integer> curMarking = getMarking();
        if (markings.contains(curMarking)) {
            return false;
        }
        markings.add(curMarking);
        for (Integer marking: getMarking()) {
            if (marking < 0) {
                return true;
            }
        }
        for (Transition t: net.getTransitionsAbleToFire()) {
            t.fire();
            if (hasParallelTransitions()) {
                return true;
            }
        }
        return false;
    }

    private void isLive() {
        List<Integer> curMarking = getMarking();
        if (markings.contains(curMarking)) {
            return;
        }
        markings.add(curMarking);
        List<Transition> ts = net.getTransitionsAbleToFire();
        if (ts.isEmpty()) {
            liveness = false;
            return;
        }
        for (Transition t: ts) {
            t.fire();
            isLive();
            List<Place> places = net.getPlaces();
            for (int i = 0; i < curMarking.size(); ++i) {
                places.get(i).setTokens(curMarking.get(i));
            }
        }
    }

    private void isStable() {
        List<Integer> curMarking = getMarking();
        if (markings.contains(curMarking)) {
            return;
        }
        markings.add(curMarking);
        for (Transition t: net.getTransitionsAbleToFire()) {
            if (!t.canFire()) {
                stability = false;
                return;
            }
            t.fire();
        }
        isStable();
    }

    private int kLimited() {
        int ans = 0;
        for (List<Integer> curMarking: markings) {
            ans = Math.max(ans, Collections.max(curMarking));
        }
        return ans;
    }

    private boolean isSafe() {
        return kLimited() == 1;
    }

    private boolean isConservative() {
        int initialSum = initialMarking.stream().reduce(Integer::sum).get();
        for (List<Integer> curMarking: markings) {
            if (curMarking.stream().reduce(Integer::sum).get() != initialSum) {
                return false;
            }
        }
        return true;
    }

    private List<Integer> getMarking() {
        List<Integer> cur = new ArrayList<>();
        for (Place p: net.getPlaces()) {
            cur.add(p.getTokens());
        }
        return cur;
    }


}
