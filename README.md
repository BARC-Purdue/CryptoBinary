# R+R: A Systematic Study of Cryptographic Function Identification Approaches in Binaries

The full paper will be available later, and the link will be updated.

## Abstract

Cryptographic functions are instrumental in securing our electronic communications and systems; yet time and time again they are mis-used, mis-implemented, or created in an ad-hoc manner. Additionally, while cryptography plays a fundamental role in securing systems, it is unfortunately also used for malicious purposes, such as hiding payloads in malware. Many such instances occur in closed-source code or binary applications, which inherently present a challenge for independent audit and analysis. Therefore, detecting the presence of cryptographic functions in a binary application can be both an indicator of malicious behavior as well as a point of interest for cryptographic analyses and vulnerability discovery.

While general purpose binary analysis and function identification techniques are themselves broad and thriving areas that could help solve these problems, a variety of work across industry and academia has focused on a subset of this space: developing techniques and tools that are specifically tailored to identifying different cryptographic primitives in binary applications. Despite the relative popularity of this work and recent advances in the space, it already lacks consistent means of evaluation or comparisons across tools. As such, we set out to conduct comprehensive reproduction and replication studies on all existing work in the space, from multiple perspectives. We noticed there is a significant gap in comparing tools, as there is no standardized testing framework allowing one to easily compare and contrast their strengths and weaknesses on a level playing field.  As such, to complement the traditional R+R studies, we developed a comprehensive testing and evaluation framework which includes a number of modern cryptographic algorithms and real world examples, that allows for the comparison of both existing and future work in a uniform manner. We then carried out reproduction and replication studies, using both their benchmarks and ours. Finally, based on our insights from the studies, we highlight major gaps in existing work, especially as they relate to modern cryptographic primitives and real-world use cases, and discuss a variety of important avenues for future work.

## Introduction

We evaluate 12 cryptographic function detection tools in our Reproduction and Replication (R+R) evaluation including

* CryptoHunt (https://github.com/s3team/CryptoHunt)
* CryptoKnight (https://github.com/AbertayMachineLearningGroup/CryptoKnight/tree/master)
* DRACA (http://www.literatecode.com/draca)
* FindCrypt2 (https://hex-rays.com/blog/findcrypt2/)
* FALKE-MC (https://dl.acm.org/doi/10.1145/3230833.3230858)
* HCD (https://webscene.ir/tools/show/Hash-and-Crypto-Detector-1.4)
* Kerckhoff (https://github.com/felixgr/kerckhoffs/tree/master)
* PEiD KANAL (http://www.dcs.fmph.uniba.sk/zri/6.prednaska/tools/PEiD/plugins/kanal.htm)
* SignSrch (https://aluigi.altervista.org/mytoolz.htm)
* Softmax Classifier (https://ieeexplore.ieee.org/abstract/document/8960303)
* Where's Crypto (https://github.com/wheres-crypto/wheres-crypto)

The majority of our evaluation aims to ensure that these tools' detection abilities can be replicated using our newly designed benchmarking and evaluation suite. The complete results are presented in Table 8 of our paper. This document provides instructions on how to obtain our evaluation results and reproduce this table.  All other graphs and figures in the paper are created from information consolidated from this table for discussion purposes and can be reproduced from this.

In our R+R evaluation, we were unable to reproduce or replicate several tools, including CryptoHunt, FALKE-MC, Kerckhoff, and Softmax Classifier, due to the lack of available source code or incompatibility with current hardware or software (please see our paper for a more in-depth discussion about this). Consequently, we cannot provide any benchmark evaluation results for these tools.

We were able to reproduce Aligot, but we could not replicate it with our benchmark. For the remaining tools, including CryptoKnight, DRACA, FindCrypt2, HCD, PEiD KANAL, SignSrch, and Where’s Crypto, we successfully replicate with our benchmark. For further discussions and details about what can and cannot be reproduced/replicated, please see our full paper.

## Dependencies

Based on the design, each tool has its own unique dependencies, which can be found via the link we provided for each tool. Since we have already included all compiled binary programs for our benchmark, there are no additional dependency requirements for running the benchmark. However, if you wish to recompile our benchmark, you will need to install `gcc`, `clang`, and `MSVC`. Some cryptographic function detection tools are not open source, and only the compiled `.exe` version is available. Therefore, to run these tools on a Linux system, Wine is required, and you can find information about how to install wine at https://www.winehq.org.

## Run Each Tool with Our Benchmarks
We saved all tools source code or binary execuable program under `tools` directory. All compiled benchmarks binary programs and their source code can be found under `crypto_function` and `mirco_benchmark` directories. Please refer to the `documentation.pdf` and each tool’s original documentation for instructions on how to run the respective tools. The complete evaluation results can be found in our paper and the documentation.
