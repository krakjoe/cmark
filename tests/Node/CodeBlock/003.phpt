--TEST--
CommonMark\Node\CodeBlock Fence Error
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock;

try {
	$block->fence = [];
} catch (TypeError $ex) {
	echo "OK";
}

?>
--EXPECT--
OK
