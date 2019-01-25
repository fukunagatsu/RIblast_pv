# RIblast_pv
RIblast_pv is a statistical significance assessment method for RNA-RNA interaction in long RNAs.

## Version
Version 1.0.0 (2017/07/05)

## Usage
RIblast_pv requires 2 options ([-i InputFileName] and [-o OutputFileName]). Input file must be an output file of RIblast ris mode. Output file includes the p-value of minimum interaction energy for each RNA-RNA pair.

## Example
    ./RIblast_pv -i input.txt -o output.txt

## License
This software is released under the MIT License, see LICENSE.txt.

## Changelogs  
2017/07/05 Version 1.0.0 was released.

## Reference
Tsukasa Fukunaga and Michiaki Hamada. "A novel method for assessing the statistical significance of RNA-RNA interactions between two long RNAs."  25, 976-978., Journal of Computational Biology (2018) 

Tsukasa Fukunaga and Michiaki Hamada. "RIblast: An ultrafast RNA-RNA interaction prediction system based on a seed-and-extension approach." 33, 2658-2665., Bioinformatics (2017)
