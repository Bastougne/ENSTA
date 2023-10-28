Require Import ZArith.


Fixpoint mult (x : nat) (y : nat) :=
  match y with
  | O => O
  | S n => x + (mult x n)
  end.


(* Correction de mult. *)
Lemma mult_correct : forall x y : nat, (mult x y) = (x * y).  (* * is Nat.mul *)
Proof.
  intro x.
  intro y.
  induction y.
  - simpl.
    (* Search (0 = _ * 0). *)
    apply mult_n_O.
  - simpl. rewrite IHy.
    (* Search (_ = _ * S _). *)
    (* Search (_ + _ = _ + _). *)
    (* Search (?a + ?b = ?b + ?a). *)
    rewrite Nat.add_comm.
    apply mult_n_Sm.
Qed.


(* Version bourine : on fait calculer. *)
Lemma trois_fois_deux : (mult 3 2) = 3 * 2.
Proof.
  compute.
  reflexivity.
Qed.


(* Version maline : on utilise le théorème que l'on s'est cassé
   la tête à démontrer. *)
Lemma beaucoup_fois_beaucoup : (mult 3000000 2000000) = 3000000 * 2000000.
Proof.
  apply mult_correct.
Qed.


(* ------------------------------------------------------------------------- *)

Lemma O_mult_O_n: forall n, 0 = mult 0 n.
  Proof.
    intro n. induction n.
    - simpl. reflexivity.
    - simpl. assumption.
  Qed.


Lemma mult_1_n_n : forall n : nat, mult 1 n = n.
Proof.
  intro. induction n.
  - simpl. reflexivity.
  - simpl. rewrite IHn. reflexivity.
Qed.
