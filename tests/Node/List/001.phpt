--TEST--
CommonMark\Node\OrderedList Tight
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

$list->setTight(true);

if ($list->isTight()) {
	echo "OK";
}
?>
--EXPECT--
OK
