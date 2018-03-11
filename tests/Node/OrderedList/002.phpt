--TEST--
CommonMark\Node\OrderedList Start
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

$list->setStart(4);

if ($list->getStart() == 4) {
	echo "OK";
}
?>
--EXPECT--
OK
