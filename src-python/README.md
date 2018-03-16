# Simple Blockchain Python Edition

### About Project
The following directory contains the blockchain implementation that was
implemented in the following [blog](https://hackernoon.com/learn-blockchains-by-building-one-117428612f46) post.

Blog post is also accompanied with a [git repo](https://github.com/dvf/blockchain)
that hosts the python implementation along
with a C# version.

### System Requirements/Prerequisites
- Python 3.6

### Installing python 3.6 on Ubuntu
- Refer to the following url if present documentation isn't sufficient:
`https://askubuntu.com/questions/865554/how-do-i-install-python-3-6-using-apt-get`

**Ubuntu 16.10 and newer**
```bash
sudo apt-get update
sudo apt-get install python3.6
```

**Ubuntu 14.04 and 16.04**
```bash
sudo add-apt-repository ppa:deadsnakes/ppa
sudo apt-get update
sudo apt-get install python3.6
```

Install pip 3.6
```bash
sudo curl https://bootstrap.pypa.io/get-pip.py | sudo python3.6
```

### Installing python 3.6 on Centos

**Centos 7**
- Refer to the following url if present documentation isn't sufficient:
`https://janikarhunen.fi/how-to-install-python-3-6-1-on-centos-7.html`

Install updates/needed utils
```bash
sudo yum update
sudo yum install yum-utils
sudo yum groupinstall development
```
Install upstream stable repo
```bash
sudo yum install https://centos7.iuscommunity.org/ius-release.rpm
```
Install python 3.6
```bash
sudo yum install python36u
```
Install pip 3.6 and other dev tools
```bash
sudo yum install python36u-pip
sudo yum install python36u-devel
```

### Installing Pipenv
- Refer to the following url if present documentation isn't sufficient:
`http://docs.python-guide.org/en/latest/dev/virtualenvs/`

While it is not necessary that this application is run in a virtual environment,
it is highly recommended that you do run it in a virtual environment.

**`pip3` refers to `pip3.6` and higher**

Pipenv
```bash
sudo pip3 install pipenv
```

### Project Setup and Run

Install project requirements
```bash
pipenv install -r requirements.txt
```

Run project<br>
**`python3` refers to `python3.6` and higher**<br>
```bash
pipenv run python3 blockchain.py
```