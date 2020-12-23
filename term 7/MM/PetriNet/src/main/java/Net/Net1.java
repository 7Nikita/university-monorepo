package Net;

import Model.Arc;
import Model.PetriNet;
import Model.Place;
import Model.Transition;
import Statistic.DynamicClassification;
import Statistic.StaticClassification;

public class Net1 {

    public static void main(String[] args) {
        PetriNet pn = new PetriNet();

        Place p1 = pn.place("p1");
        Place p2 = pn.place("p2");
        Place p3 = pn.place("p3", 1);
        Place p4 = pn.place("p4", 1);
        Place p5 = pn.place("p5");

        Transition a = pn.transition("a");
        Transition b = pn.transition("b");
        Transition c = pn.transition("c");
        Transition d = pn.transition("d");

        // p4 -> a -> p1 -> c -> p4
        Arc p4a = pn.arc("p4a", p4, a);
        Arc ap1 = pn.arc("ap1", a, p1);
        Arc p1c = pn.arc("p1c", p1, c);
        Arc cp4 = pn.arc("cp4", c, p4);

        // p4 -> d -> p5
        Arc p4d = pn.arc("p4d", p4, d);
        Arc dp5 = pn.arc("dp5", d, p5);

        // p2 -> c -> p3 -> b -> p2
        Arc p2c = pn.arc("p2c", p2, c);
        Arc cp3 = pn.arc("cp3", c, p3);
        Arc p3b = pn.arc("p3b", p3, b);
        Arc bp2 = pn.arc("bp2", b, p2);


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
