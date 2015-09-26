# cdrepo

Make a script's references safe against symlinks – with a shebang.

```
$ npm install -g cdrepo
$ cat `which cmd`
#!/usr/bin/env cdrepo
d=$1
echo "$d"
shift
...
$ cmd
~/bin/cmd
```

