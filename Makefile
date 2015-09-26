all: cdrepo

cdrepo: cdrepo.hs
	cabal build

