#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node {
  char name[20];
  int runs, fours, sixes, balls;
  float s_rate;
  struct node *next;
};
struct bowl {
  char name[20];
  int runs, wkts, mdn, overs;
  float econ;
  struct bowl *next;
};
struct teamname {
  char name[30];
  struct teamname *next;
};
struct teamname *t1, *t2;
struct node *team1, *team2;
struct bowl *tm1, *tm2,*newtemp;
int b_man1[10], b_man2[10], bowler[10], top1 = -1, top2 = -1, top3 = -1;
void inning_1score();
void inning_2score();
void match_result();
void insert();
void display();
int toss();
void displaybl();
int total = 0, totalw = 0, target = 0, played = 1, balls, op;
struct bowl *search(struct bowl *x, char *y) {
  while (x != NULL) {
    if (!strcmp(x->name, y)) {
      return x;
    }
    x = x->next;
  }
  return NULL;
}
struct teamname *setname(struct teamname *t1) {
  char name[50];
  struct teamname *new = (struct teamname *)malloc(sizeof(struct teamname));
  printf("TEAM NAME : ");
  scanf("%s", new->name);
  new->next=NULL;
  t1 = new;
  struct teamname *cur;
  cur = t1;
  for (int i = 1; i <= 11; i++) {
    new = (struct teamname *)malloc(sizeof(struct teamname));
    printf("PLAYER %d : ", i);
    scanf("%s", name);
    strcpy(new->name,name);
    cur->next = new;
    cur = cur->next;
  }
  cur->next = NULL;
  return t1;
}
void insert(struct bowl *new, int tmno) {
  struct bowl *tmp;
  if (tmno == 2) {
    if (tm1 == NULL) {
      tm1 = new;
    } else {
      tmp = tm1;
      newtemp = (struct bowl *)malloc(sizeof(struct bowl));
      while (tmp->next != NULL) {
        tmp = tmp->next;
      }
      tmp->next = new;
    }
  } else {
    if (tm2 == NULL) {
      tm2 = new;
      newtemp = (struct bowl *)malloc(sizeof(struct bowl));
    } else {
      tmp = tm2;
      newtemp = (struct bowl *)malloc(sizeof(struct bowl));
      while (tmp->next != NULL) {
        tmp = tmp->next;
      }
      tmp->next = new;
    }
  }
}
void bowling(int *bowler, int top3, int tmno, struct bowl *x) {
  int wkt = 0, mdn = 0;
  float econ, truns = 0;
  for (int i = top3; i >= 0; i--) {
    if (bowler[i] == -2) {
      wkt++;
    } else if (bowler[i] != -1) {
      truns = truns + bowler[i];
    } else if (bowler[i] == -1) {
      truns++;
    }
  }
  if (truns == 0) {
    mdn++;
  }
  if (played == 1) {
    total = total + truns;
  }
  if (tmno == 2) {
    struct bowl *tmp = search(tm1, x->name);
    if (tmp == NULL) {
      econ = truns / 1;
      x->econ = econ;
      x->mdn = mdn;
      x->next = NULL;
      x->overs = 1;
      x->runs = truns;
      x->wkts = wkt;
      insert(x, tmno);
    } else {
      econ = (truns + tmp->runs) / (1 + tmp->overs);
      tmp->econ = econ;
      tmp->mdn = tmp->mdn + mdn;
      tmp->overs = tmp->overs + 1;
      tmp->runs = tmp->runs + truns;
      tmp->wkts = tmp->wkts + wkt;
      free(x);
    }
  }
  else {
    struct bowl *tmp = search(tm2, x->name);
    if (tmp == NULL) {
      econ = truns / 1;
      x->econ = econ;
      x->mdn = mdn;
      x->next = NULL;
      x->overs = 1;
      x->runs = truns;
      x->wkts = wkt;
      insert(x, tmno);
    } else {
      econ = (truns + tmp->runs) / (1 + tmp->overs);
      tmp->econ = econ;
      tmp->mdn = tmp->mdn + mdn;
      tmp->overs = tmp->overs + 1;
      tmp->runs = tmp->runs + truns;
      tmp->wkts = tmp->wkts + wkt;
      free(x);
    }
  }
}
int wktcount(struct bowl *temp) {
  int count = 0;
  while (temp != NULL) {
    count = count + temp->wkts;
    temp = temp->next;
  }
  printf("%d", count);
  return count;
}
void inning_1score() {
  printf("------------------------------------------------------------\n");
  printf("\t\t1st INNINGS\t\t\n");
  printf("------------------------------------------------------------\n");
  printf("````````````````````````````````````````````````````````````\n");
  printf("\t\t  BATTING\t\t\n");
  printf("------------------------------------------------------------\n");
  display(team1);
  printf("````````````````````````````````````````````````````````````\n");
  printf("\t\t  BOWLING\t\t\n");
  printf("------------------------------------------------------------\n");
  displaybl(tm2);
  printf("============================================\n");
  printf("%s : ", t1->name);
  printf("%d/", total);
  wktcount(tm2);
  printf("\n");
  printf("============================================\n");
}
void inning_2score() {
  printf("------------------------------------------------------------\n");
  printf("\t\t2nd INNINGS\t\t\n");
  printf("------------------------------------------------------------\n");
  printf("````````````````````````````````````````````````````````````\n");
  printf("\t\t  BATTING\t\t\n");
  printf("------------------------------------------------------------\n");
  display(team2);
  printf("````````````````````````````````````````````````````````````\n");
  printf("\t\t  BOWLING\t\t\n");
  printf("------------------------------------------------------------\n");
  displaybl(tm1);
  printf("============================================\n");
  printf("%s : ", t2->name);
  printf("%d/", target);
  wktcount(tm1);
  printf("\n");
  printf("============================================\n");
}
int wktcount1(struct bowl *temp) {
  int count = 0;
  while (temp != NULL) {
    count = count + temp->wkts;
    temp = temp->next;
  }
  return count;
}
void match_result() {
  int t = wktcount1(tm1);
  if (total > target) {
    printf("\n%s WON BY %d RUNS\n\n", t1->name, total - target);
  } else if (target > total) {
    printf("\n%s WON BY %d WICKETS\n\n", t2->name, 10 - t);
  } else if (target == total) {
    printf("\nMATCH DRAWN:\n");
    /*over(2,1);
    over(1,1);*/
  }
}
void score(int *player, int balls, struct node *new, int tmno) {
  struct node *tmp;
  int four = 0, six = 0;
  float strikerate = 0, run = 0;
  for (int i = balls; i >= 0; i--) {
    if (player[i] == 4) {
      run = run + 4;
      four=four+1;
    } else if (player[i] == 6) {
      run = run + 6;
      six=six+1;
    } else {
      run = run + player[i];
    }
  }
  new->fours = four;
  new->sixes = six;
  new->runs = run;
  new->balls = balls + 1;
  strikerate = (run / (balls + 1)) * 100.00;
  new->s_rate = strikerate;
  new->next = NULL;
  if (tmno == 1) {
    if (team1 == NULL) {
      team1 = new;
    } else {
      tmp = team1;
      while (tmp->next != NULL) {
        tmp = tmp->next;
      }
      tmp->next = new;
    }
  } else {
    if (team2 == NULL) {
      team2 = new;
    } else {
      tmp = team2;
      while (tmp->next != NULL) {
        tmp = tmp->next;
      }
      tmp->next = new;
    }
  }
}
void over(int tmno, int op) {
  struct node *strike = (struct node *)malloc(sizeof(struct node));
  struct node *nonstrike = (struct node *)malloc(sizeof(struct node));
  struct bowl *bowlr = (struct bowl *)malloc(sizeof(struct bowl));
  int ball = 0, runs=0, wkt = 0, overs = 0;
  int f = 1;
  printf("STRIKER: ");
  scanf("%s", strike->name);
  printf("NON-STRIKER: ");
  scanf("%s", nonstrike->name);
  printf("BOWLER: ");
  scanf("%s", bowlr->name);
  printf("\nPLEASE CHOOSE BELOW OPTIONS:\nWICKET\t\t  = -2\nWIDE OR NO-BALL   = -1\nDOT   \t\t  = 0\n");
  printf("1-RUN\t\t  = 1\n2-RUNS\t\t  = 2\n3-RUNS    \t  = 3\n4-RUNS\t\t  = 4\n6-RUNS\t\t  = 6\n");
  while (overs <= op && total >= target) {
    while (ball < 6 && total >= target) {
      printf("BALL %d : ", ball + 1);
      scanf("%d", &runs);
      if (wkt == 10)
        break;
      if (f == 1) {
        if (runs == -1) {
          top3++;
          bowler[top3] = -1;
          if (played == -1) {
            target = target + 1;
          }
          continue;
        } else if (runs == -2) {
          wkt++;
          ball++;
          top1++;
          top3++;
          b_man1[top1] = 0;
          score(b_man1, top1, strike, tmno);
          top1 = -1;
          bowler[top3++] = -2;
          strike = (struct node *)malloc(sizeof(struct node));
          printf("NEW BATSMAN : ");
          scanf("%s", strike->name);
        } else if (runs % 2 == 0) {
          top1++;
          top3++;
          ball++;
          bowler[top3] = b_man1[top1] = runs;
          if (played == -1) {
            target = target + runs;
          }
        } else if (runs % 2 != 0) {
          top1++;
          ball++;
          top3++;
          bowler[top3] = b_man1[top1] = runs;
          if (played == -1) {
            target = target + runs;
          }
          f = 0;
        }
      } else {
        if (runs == -1) {
          top3++;
          bowler[top3]++;
          target = target + 1;
          continue;
        } else if (runs == -2) {
          wkt++;
          ball++;
          top2++;
          top3++;
          b_man2[top2] = 0;
          bowler[top3++] = -2;
          score(b_man2, top2, nonstrike, tmno);
          top2 = -1;
          nonstrike = (struct node *)malloc(sizeof(struct node));
          printf("NEW BATSMAN : ");
          scanf("%s", nonstrike->name);
        } else if (runs % 2 == 0) {
          top2++;
          top3++;
          ball++;
          if (played == -1) {
            target = target + runs;
          }
          bowler[top3] = b_man2[top2] = runs;
        } else if (runs % 2 != 0) {
          top2++;
          ball++;
          top3++;
          if (played == -1) {
            target = target + runs;
          }
          bowler[top3] = b_man2[top2] = runs;
          f = 1;
        }
      }
    }
    if (f == 0) {
      f = 1;
    } else {
      f = 0;
    }
    overs++;
    bowling(bowler, top3, tmno, bowlr);
    top3 = -1;
    if (overs == op) {
      score(b_man1, top1, strike, tmno);
      score(b_man2, top2, nonstrike, tmno);
      break;
    }
    if (total < target) {
      break;
    }
    ball = 0;
    bowlr = (struct bowl *)malloc(sizeof(struct bowl));
    printf("NEW BOWLER: ");
    scanf("%s", bowlr->name);
  }
  top1 = -1, top2 = -1, top3 = -1;
}
int toss(struct teamname *t1, struct teamname *t2) {
  char tss[20], ch[5];
  printf("\nTOSS WON BY %s OR %s : ", t1->name, t2->name);
  scanf("%s", tss);
  while (1) {
    if (!strcmp(tss, t1->name)) {
      printf("BAT OR BOWL ?   ");
      scanf("%s", ch);
      if (!strcmp(ch, "BAT")) {
        printf("%s CHOOSE TO BAT FIRST\n", t1->name);
        return 1;
      } else if (!strcmp(ch, "BOWL")) {
        printf("%s CHOOSE TO BOWL FIRST\n", t1->name);
        return 2;
      }
    } else if (!strcmp(tss, t2->name)) {
      printf("BAT OR BOWL ?   ");
      scanf("%s", ch);
      if (!strcmp(ch, "BAT")) {
        printf("%s CHOOSE TO BAT FIRST\n", t2->name);
        return 3;
      } else if (!strcmp(ch, "BOWL")) {
        printf("%s CHOOSE TO BOWL FIRST\n", t2->name);
        return 4;
      }
    } else {
      printf("CHOOSE CORRECT CHOICE\n");
    }
  }
}
void display(struct node *tmp) {
  printf("------------------------------------------------------------\n");
  printf("NAME\t\tRUNS\tBALLS\t4'S\t6'S\tSTRIKE-RATE\n");
  printf("------------------------------------------------------------\n");
  while (tmp != NULL) {
    printf("%s\t\t", tmp->name);
    printf(" %d\t  %d\t %d\t %d\t ", tmp->runs, tmp->balls, tmp->fours,
           tmp->sixes);
    printf(" %.2f\n", tmp->s_rate);
    tmp = tmp->next;
  }
}
void displaybl(struct bowl *tmp) {
  printf("------------------------------------------------------------\n");
  printf("NAME\t\tOVERS\tMAIDEN\tRUNS\tWICKETS\t ECONOMY\n");
  printf("------------------------------------------------------------\n");
  while (tmp != NULL) {
    printf("%s\t\t", tmp->name);
    printf("%d \t%d \t%d \t%d   \t", tmp->overs, tmp->mdn, tmp->runs,
           tmp->wkts);
    printf("  %.2f\n", tmp->econ);
    tmp = tmp->next;
  }
}
void displayt1() {
  struct teamname *cur_node1 = t1, *cur_node2 = t2;
  while (cur_node1 != NULL && cur_node2 != NULL) {
    printf("\t%s\t\t\t\t\t\t\t\t\t\t%s\n", cur_node1->name, cur_node2->name);
    cur_node1 = cur_node1->next;
    cur_node2 = cur_node2->next;
  }
}
int main() {
  t1 = setname(t1);
  t2 = setname(t2);
  int t = toss(t1, t2);
  float ov;
  struct teamname *cur_node1 = t1, *cur_node2 = t2;
  printf("\nNO. OF OVERS: ");
  scanf("%f", &ov);
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  printf("\t\t\t\tPLAYING 11 ( %s vs %s )\n", cur_node1->name, cur_node2->name);
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  displayt1();
  if (t == 1) {
    over(1, ov);
    played = -1;
    printf("============================================\n");
    printf("%s : ", t1->name);
    printf("%d/", total);
    wktcount(tm2);
    printf("\t\t\tC.R.R : %0.1f\n", total / ov);
    printf("============================================\n");
    printf("%s NEED %d FROM %0.1f BALLS\t", t2->name, total + 1, ov * 6.0);
    printf("R.R:%0.2f \n", ((total + 1.0) / ov));
    over(2, ov);
    printf("============================================\n");
    printf("%s : ", t2->name);
    printf("%d/", target);
    wktcount(tm1);
    printf("\n");
    printf("============================================\n");
  } else if (t == 2) {
    over(2, ov);
    played = -1;
    printf("============================================\n");
    printf("%s : ", t2->name);
    printf("%d/", total);
    wktcount(tm1);
    printf("\t\t\tC.R.R : %0.1f\n", total / ov);
    printf("============================================\n");
    printf("%s NEED %d FROM %0.1f BALLS\t", t1->name, total + 1, ov * 6);
    printf("R.R:%0.2f \n", ((total + 1.0) / ov));
    over(1, ov);
    printf("============================================\n");
    printf("%s : ", t1->name);
    printf("%d/", target);
    wktcount(tm2);
    printf("\n");
    printf("============================================\n");
  } else if (t == 3) {
    over(2, ov);
    played = -1;
    printf("============================================\n");
    printf("%s : ", t2->name);
    printf("%d/", total);
    wktcount(tm1);
    printf("\t\t\tC.R.R : %0.1f\n", total / ov);
    printf("============================================\n");
    printf("%s NEED %d FROM %0.1f BALLS\t", t1->name, total + 1, ov * 6);
    printf("R.R:%0.2f \n", ((total + 1.0) / ov));
    over(1, ov);
    printf("============================================\n");
    printf("%s : ", t1->name);
    printf("%d/", target);
    wktcount(tm2);
    printf("\n");
    printf("============================================\n");
  } else if (t == 4) {
    over(1, ov);
    played = -1;
    printf("============================================\n");
    printf("%s : ", t1->name);
    printf("%d/", total);
    wktcount(tm2);
    printf("\t\t\tC.R.R : %0.1f\n", total / ov);
    printf("============================================\n");
    printf("%s NEED %d FROM %0.1f BALLS\t", t2->name, total + 1, ov * 6.0);
    printf("R.R:%0.2f \n", ((total + 1.0) / ov));
    over(2, ov);
    printf("============================================\n");
    printf("%s : ", t2->name);
    printf("%d/", target);
    wktcount(tm1);
    printf("\n");
    printf("============================================\n");
  }
  int choice;
  while (1) {
    printf("1.TEAM DETAILS\n2.INNINGS-1\n3.INNINGS-2\n4.MATCH RESULT\n5.EXIT\n");
    printf("ENTER OPTION: \n");
    scanf("%d", &choice);
    switch (choice) {
    case 1:
      displayt1();
      break;
    case 2:
      inning_1score();
      break;
    case 3:
      inning_2score();
      break;
    case 4:
      match_result();
      break;
    case 5:
      return 0;
    }
  }
  return 0;
}
