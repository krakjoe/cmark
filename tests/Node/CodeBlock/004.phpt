--TEST--
CommonMark\Node\CodeBlock Fence None
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock;

if (!$block->getFence()) {
	echo "OK";
}
?>
--EXPECT--
OK
