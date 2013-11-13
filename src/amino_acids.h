/**
 * Contains the definitions of the amino acids.
 *
 * !!! IMPORTANT !!!
 * The order of the fields must match the order of the amino acid
 * sequence!
 */


#define NUMBER_OF_AMINO_ACIDS  (20)

// Enum for the amino acids
enum amino_acid_t {
  ILE = 0,
  ALA,
  ARG,
  ASP,
  CYS,
  GLU,
  GLY,
  HIS,
  LEU,
  LYS,
  MET,
  GLN,
  PHE,
  PRO,
  SER,
  THR,
  TRP,
  ASN,
  TYR,
  VAL
};

// Full Names
char const * const aa_full_name[] = {
  "Isoleucine",
  "Alanine",
  "Arginine",
  "Aspartic Acid",
  "Cysteine",
  "Glutamic Acid",
  "Glycine",
  "Histidine",
  "Leucine",
  "Lysine",
  "Methionine",
  "Glutamine",
  "Phenylalanine",
  "Proline",
  "Serine",
  "Threonine",
  "Tryptophan",
  "Asparagine",
  "Tyrosine",
  "Valine"
};

// TLA Names
char const * const aa_tla_name[] = {
  "Ile",
  "Ala",
  "Arg",
  "Asp",
  "Cys",
  "Glu",
  "Gly",
  "His",
  "Leu",
  "Lys",
  "Met",
  "Gln",
  "Phe",
  "Pro",
  "Ser",
  "Thr",
  "Trp",
  "Asn",
  "Tyr",
  "Val"
};

// Polarization
char const * const aa_polarized[] = {
  "nonpolar",
  "nonpolar",
  "polar cationic",
  "polar anionic",
  "polar uncharged",
  "polar anionic",
  "nonpolar",
  "polar cationic",
  "nonpolar",
  "polar cationic",
  "nonpolar",
  "polar uncharged",
  "nonpolar",
  "nonpolar",
  "polar uncharged",
  "polar uncharged",
  "nonpolar",
  "polar uncharged",
  "polar uncharged",
  "nonpolar"
};

// Functional Group
char const * const aa_func_group[] = {
  "",
  "",
  "pKa (guanidine)",
  "pKa (COOH)",
  "pKa (sulfhydryl)",
  "pKa (COOH)",
  "",
  "pKa (imidazole)",
  "",
  "pKa (NH3+)",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "pKa (phenol)",
  ""
};

// pKa Value
char const * const aa_pKa[] = {
  "",
  "",
  "8.99",
  "3.90",
  "8.37",
  "4.07",
  "",
  "6.04",
  "",
  "10.54",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "10.46",
  ""
};
