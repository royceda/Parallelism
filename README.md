# Parallelism
Simulation of atom

ATTENTION ! changement de domaine.
Utilisez le domaine emi.u-bordeaux.fr pour vos accès depuis extérieur :
- https://services.emi.u-bordeaux.fr
- http://www.emi.u-bordeaux.fr
- ssh login@jaguar.emi.u-bordeaux.fr


touches:

g: graviter
r: rebond


Avant tout vérifier que le CPU se trouver sur 0 ou 1 (j'ai mis 0 partout :/)
1. séquentiel: exécuter script_seq.sh
2. Sans tri selon z dans openmp.c: Commenter omp_force et décommenter omp_force en dessous > Exécuter script_num_thread > garder le fichier res_num_thread.data et le renommer pour plot plus tard
3. Avec tri selon z: Dans openmp.c Décommenter la première omp_force et commenter la deuxieme > Exécuter script_num_thread > garder le fichier res_num_thread.data et le renommer pour plot plus tard
4. Les schedule: Dans openmp.c décommenter tous les schedule(static) dans les #pragma omp parallel for > Mettre dans script_schedule le meilleur nombre de threads obtenu sur le test 3 > exécuter script_schedule.sh