--TEST--
CommonMark\Node\CodeBlock constructor literal and fence
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock("FENCE", "LITERAL");

echo $block->fence . "\n";
echo $block->literal;
?>
--EXPECT--
FENCE
LITERAL
