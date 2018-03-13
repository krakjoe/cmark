--TEST--
CommonMark\Node\CodeBlock Fence Error
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock;

try {
	$block->setFence([]);
} catch (TypeError $ex) {
	echo "OK";
}

?>
--EXPECT--
OK
