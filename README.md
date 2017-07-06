# RIblast_pv
RIblast_pv is a statistical significance assessment method for RNA-RNA interaction in long RNAs.

## Version
Version 1.0.0 (2017/07/05)

## Usage
RIblast_pv requires 2 options ([-i InputFileName] and [-o OutputFileName]). Input file must be an output file of RIblast ris mode. Output file includes the p-value of minimum interaction energy for each RNA-RNA pair.

## Example
    ./RIblast db -i dbRNA.fa -o test_db
    ./RIblast ris -i queryRNA.fa -o output.txt -d test_db
