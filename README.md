# hello-dlopen
Build and Run the application that prints the prediction on screen
```
make run
```

In a different window edit predict.c and recompile predict.so while the above applications is still running
```
emacs predict.c # make changes as required
rm -f obj/predict.so ; make obj/predict.so
```

Where the application is running, Press u key and it should now use the new predictor that we recompiled in previous step without requiring application to restart.
