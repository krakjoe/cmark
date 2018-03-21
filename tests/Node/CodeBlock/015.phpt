--TEST--
CommonMark\Node\CodeBlock constructor literal
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock("OK");

echo $block->literal;
?>
--EXPECT--
OK
