--TEST--
CommonMark\Node\CodeBlock Fence Error
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock;

try {
	$block->setFence([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}

?>
--EXPECT--
OK
