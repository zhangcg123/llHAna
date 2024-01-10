for ITHPART in {0..9}; do
    export ITHPART
    for ITH in {0..9}; do
        export ITH
        gaudirun.py llh.py &
    done
    # wait for the inner loop to finish
    wait
done
wait