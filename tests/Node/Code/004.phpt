--TEST--
CommonMark\Node\Code incorrect construction
--FILE--
<?php
$code = new CommonMark\Node\Code("OK");

echo $code->literal;
?>
--EXPECT--
OK
