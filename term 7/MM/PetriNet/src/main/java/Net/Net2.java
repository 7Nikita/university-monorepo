package Net;

import Model.Arc;
import Model.PetriNet;
import Model.Place;
import Model.Transition;
import Statistic.DynamicClassification;
import Statistic.StaticClassification;

public class Net2 {

    public static void main(String[] args) {
        PetriNet pn = new PetriNet();

        Place p1 = pn.place("p1", 1);
        Place p2 = pn.place("p2");
        Place p3 = pn.place("p3");
        Place p4 = pn.place("p4");
        Place p5 = pn.place("p5");
        Place p6 = pn.place("p6", 1);

        Transition t1 = pn.transition("t1");
        Transition t2 = pn.transition("t2");
        Transition t3 = pn.transition("t3");
        Transition t4 = pn.transition("t4");

        // P1 -> t1 -> P2P6P3
        Arc p1t1 = pn.arc("p1t1", p1, t1);
        Arc t1p2 = pn.arc("t1p2", t1, p2);
        Arc t1p3 = pn.arc("t1p3", t1, p3);
        Arc t1p6 = pn.arc("t1p6", t1, p6);

        // P2 -> t2 -> P4
        Arc p2t2 = pn.arc("p2t2", p2, t2);
        Arc t2p4 = pn.arc("t2p4", t2, p4);

        // P3 -> t3 -> P5
        Arc p3t3 = pn.arc("p3t3", p3, t3);
        Arc t3p5 = pn.arc("t3p5", t3, p5);

        // P4P5P6 -> t4 -> p1
        Arc p4t4 = pn.arc("p4t4", p4, t4);
        Arc p5t4 = pn.arc("p5t4", p5, t4);
        Arc p6t4 = pn.arc("p6t4", p6, t4);
        Arc t4p1 = pn.arc("t4p1", t4, p1);

        DynamicClassification dc = new DynamicClassification(pn);
        System.out.println(dc.getPossibleMarkings());
        System.out.println("Is parallel: " + dc.isParallelness());
        System.out.println("K-Limited: "+ dc.getKLimitation());
        System.out.println("Safe: " + dc.isSafety());
        System.out.println("Conservative: " + dc.isConservativeness());
        System.out.println("Live: " + dc.isLiveness());
        System.out.println("Stability: " + dc.isStability());

        StaticClassification sc = new StaticClassification(pn);
        System.out.println("Automatic net: " + sc.isAutomatic());
        System.out.println("Marked graph: " + sc.isMarkedGraph());
        System.out.println("Conflict net: " + sc.isConflict());
        System.out.println("Free choice net: " + sc.isFreeChoice());
    }

}
