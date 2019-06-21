# HEffectIVe

The project HEffectIVe (for Heterogeneous Effects Inference and Verification) is composed of 1) librairies for copumtation of Minimal Cut Sets (MCS) (/releaseprimeext), and 2) an xml open-psa parser (/releases/HEffectIVe-openpsa.exe).

The latter can be used in command line as follows:

HEffectIVe-openpsa.exe "ft1" "sample-openpsa/simple-ft1.xml" -dot

where "ft1" is the name of the fault tree for which MCS will be computed, "sample-openpsa/simple-ft1.xml" is the xml open-psa describing the fault tree "ft1" as being a boolean formula expressed with boolean connectives AND, OR, NOT, ..., and -dot is an option allowing the generation of a dot file for the graphical depiction of the BDD built for the fault tree formula.

HEffectIVe is being under review process to be part of Eclipse Formal Modeling Project (https://projects.eclipse.org/projects/modeling.efm)


