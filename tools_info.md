
# Git record #

[Reference](https://mp.weixin.qq.com/s/MCT2-vUbPg5PxMacpyoFYw)

## First setting ##

    git config --global user.name "John Doe"
    git config --global user.email johndoe@example.com

    cd ~/.ssh
    ssh-keygen
    cat ~/.ssh/id_rsa.pub

## Change remote git ##

    git remote rm origin
    git remote add origin git@github.com:michaelliao/learngit.git
    git branch --set-upstream-to=origin/master master
