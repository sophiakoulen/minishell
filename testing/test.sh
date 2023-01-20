#/bin/bash

MINI=../minishell

echo testing minishell...

# test 0
$MINI >>act_out0 2>>act_err0 <<END
|
END
bash >>exp_out0 2>>exp_err0 <<END
|
END
diff act_out0 exp_out0 >>test0.diff
diff act_err0 exp_out0 >>test0.diff
rm *0

# test 1
$SH >>act_out1 2>>act_err1 <<END
echo |
END
bash >>exp_out1 2>>exp_err1 <<END
echo |
END
diff act_out1 exp_out1 >>test1.diff
diff act_err1 exp_out1 >>test1.diff
rm *1

# test 2
$SH >>act_out2 2>>act_err2 <<END
|||<>
END
bash >>exp_out2 2>>exp_err2 <<END
|||<>
END
#diff act_out2 exp_out2 >>test2.diff
#diff act_err2 exp_out2 >>test2.diff
#rm *2