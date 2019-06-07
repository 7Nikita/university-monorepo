package com.nikita;

import java.util.ArrayList;
import java.util.Scanner;

public class task21 {

    static class Pair {
        int f;
        int s;
        public Pair (int f, int s) {
            this.f = f;
            this.s = s;
        }
    }

    static int n;

    static Pair[] dp;
    static ArrayList<Integer>[] tr;

    static void dfs(int cur, int from){
        if (tr[cur].size() == 1 && from != -1){
            dp[cur] = new Pair(0, 0);
            return;
        }

        int s = 0;

        for (int i = 0; i < tr[cur].size(); ++i){
            if (tr[cur].get(i) == from)
                continue;
            dfs(tr[cur].get(i), cur);
            s += dp[tr[cur].get(i)].s;
        }

        int m = -1;

        for (int i = 0; i < tr[cur].size(); ++i){
            if (tr[cur].get(i) == from)
                continue;
            int tmp = s - dp[tr[cur].get(i)].s + dp[tr[cur].get(i)].f;
            if (tmp > m)
                m = tmp;
        }

        dp[cur] = new Pair(s, m + 1);
    }

    public static void main(String[] args) {

        var sc = new Scanner(System.in);

        n = sc.nextInt();

        tr = new ArrayList[n];
        dp = new Pair[n];

        for (int i = 0; i < n; ++i)
            tr[i] = new ArrayList<Integer>();

        for (int i = 0; i < n - 1; ++i){
            int a, b;
            a = sc.nextInt();
            b = sc.nextInt();
            --a;
            --b;
            tr[a].add(b);
            tr[b].add(a);
        }

        dfs(0, -1);

        System.out.println(Math.max(dp[0].f, dp[0].s));

    }

}
