--TEST--
CommonMark\Node\CodeBlock Fence None
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock;

if (!$block->fence) {
	echo "OK";
}
?>
--EXPECT--
OK
