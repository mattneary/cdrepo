# cdrepo

Make a script's references safe against symlinks – with a shebang.

```
$ npm install -g cdrepo
$ cat `which cmd`
#!/usr/bin/env cdrepo
echo "$0"
...
$ cmd
~/bin/cmd
```

