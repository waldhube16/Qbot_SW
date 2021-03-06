#!/bin/sh
#Python Version: 3.7.9 64bit
#download and install miniconda from this page: https://docs.conda.io/en/latest/miniconda.html#linux-installers
#create new environment
conda create -name QBot

#install all other packages that are possible with anaconda
#...
#after that install packages with pip
pip install -r PipReqs.txt
#dont change anaconda packages afterwards: https://docs.conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html#viewing-a-list-of-the-packages-in-an-environment