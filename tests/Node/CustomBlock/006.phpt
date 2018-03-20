--TEST--
CommonMark\Node\CustomBlock onEnter Empty
--FILE--
<?php
$node = new CommonMark\Node\CustomBlock;

if (!$node->onEnter) {
	echo "OK";
}
?>
--EXPECT--
OK
