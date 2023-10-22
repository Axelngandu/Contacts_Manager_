#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom :     NGANDU                    Prénom :    Axel                 */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau
	int idx = rep->nb_elts;
    if (rep->nb_elts < MAX_ENREG)
	{
	    rep->tab[idx] = enr;
	    compact(rep->tab[idx].tel);
        printf("%s %s %s\n",rep->tab[idx].nom, rep->tab[idx].prenom, rep->tab[idx].tel);
        modif = true;
        rep->nb_elts++;
	}
	else {
		return(ERROR);
	}


#else
#ifdef IMPL_LIST

	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0)
        {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
			//
			// compléter code ici pour Liste
			//
			//
			//

	}


#endif

#endif


	return(OK);

} /* fin ajout */
  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/
#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire *rep, int indice)
{

	// compléter code ici pour tableau
	if (rep->nb_elts >= 1)
    {                                                       /* s'il y a au moins un element ds le tableau et que l'indice pointe a l'interieur */
        rep->tab[indice] = rep->tab[rep->nb_elts-1];
        rep->nb_elts -= 1;		                            /* ds ts les cas, il y a un element en moins */
		modif = true;
    }

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) {

	int ret=DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0);
	}
#endif
#endif


  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	// code à compléter ici


} /* fin affichage_enreg */
  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	// code à compléter ici
	// comme fonction affichage_enreg, mais avec présentation alignées des infos
	int i,j,k;
	char msg1[31]={0},msg2[31]={},msg3[31]={0};
	i = strlen(enr.nom);
	j = strlen(enr.prenom);
	k = strlen(enr.tel);
	for(int l=0;l<=30-i;l++)
        msg1[l]=' ';
    for(int l=0;l<=30-j;l++)
        msg2[l]=' ';
    for(int l=0;l<=30-k;l++)
        msg3[l]=' ';

    printf("|%s%s|%s%s|%s\n",enr.nom,msg1,enr.prenom,msg2,enr.tel);

} /* fin affichage_enreg */


  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	if(strcmp(enr1.nom,enr2.nom)>0)
        return (true);
    else
        if(strcmp(enr1.nom,enr2.nom)==0)
            if(strcmp(enr1.prenom,enr2.prenom)>0)
                return (true);
        return(false);
}

/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire *rep)
{

#ifdef IMPL_TAB
	// ajouter code ici pour tableau
int SIZE = rep->nb_elts;
int i,j;
Enregistrement tmp;

  for (i=0 ; i < SIZE-1; i++)
  {
    for (j=0 ; j < SIZE-i-1; j++)
    {
      if (est_sup(rep->tab[j],rep->tab[j+1]))
      {
        tmp = rep->tab[j];
        rep->tab[j] = rep->tab[j+1];
        rep->tab[j+1] = tmp;
      }
    }
  }



#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours triée
#endif
#endif


	rep->est_trie = true;

} /* fin trier */

  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de début de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;

	ind_fin = rep->nb_elts - 1; // indice de fin à ne pas dépasser
	strncpy_s(tmp_nom, _countof(tmp_nom) , nom, _TRUNCATE);

#ifdef IMPL_TAB
							// ajouter code ici pour tableau

    while ((i <= ind_fin) && (!trouve))
	{
        strncpy_s(tmp_nom2, _countof(tmp_nom2) , rep->tab[i].nom, _TRUNCATE);
		if (strcmp(tmp_nom, tmp_nom2) == 0)
			trouve = true;
		else
			i++;
	}

#else
#ifdef IMPL_LIST
							// ajouter code ici pour Liste

#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char *s)
{
	// compléter code ici
	int j;
	j= strlen(s);
	for(int i=0;i<j;i++)
    {
        if(!(isdigit(s[i])))
        {
            for(int k=i;k<=j;k++)
            {
                s[k]=s[k+1];
            }
            j--;
            i--;
        }
    }
	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;
	errno_t err;
                /* le fichier */
#ifdef IMPL_TAB
	// ajouter code ici pour tableau
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "w")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		for(int i=0;i<rep->nb_elts;i++)
        fprintf(fic_rep,"%s;%s;%s\n", rep->tab[i].nom ,rep->tab[i].prenom,rep->tab[i].tel);
        printf("%d",rep->nb_elts);
    }
    fclose(fic_rep);


#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;

	_set_errno(0);
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
														// ajouter code implemention liste
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */
