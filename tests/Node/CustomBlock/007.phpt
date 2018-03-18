--TEST--
CommonMark\Node\CustomBlock onLeave Empty
--FILE--
<?php
$node = new CommonMark\Node\CustomBlock;

if (!$node->getOnLeave()) {
	echo "OK";
}
?>
--EXPECT--
OK
