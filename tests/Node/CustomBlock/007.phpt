--TEST--
CommonMark\Node\CustomBlock onLeave Empty
--FILE--
<?php
$node = new CommonMark\Node\CustomBlock;

if (!$node->onLeave) {
	echo "OK";
}
?>
--EXPECT--
OK
