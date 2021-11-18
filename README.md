# hello-dlopen
Build and Run the application that prints the prediction on screen
```
make run
```

In a different window edit predict.c and recompile predict.so
```
emacs predict.c # make changes as required
make obj/predict.so
```

Where the application is running, Press u key and it should now use the new predictor that we recompiled in previous step
