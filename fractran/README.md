# FRACTRAN

Created by John Conway, FRACTRAN is an esolang consisting of an integer n and a list of fractions. The program is run by updating n according to the following rules:
1. for the first fraction f in the list for which nf is an integer, replace n with nf
2. repeat until there is no fraction f that satisfies rule 1
