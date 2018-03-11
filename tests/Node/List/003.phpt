--TEST--
CommonMark\Node\OrderedList Delimiter Period
--FILE--
<?php
$list = new CommonMark\Node\OrderedList;

$list->setDelimitPeriod();

if ($list->hasPeriodDelim()) {
	echo "OK";
}
?>
--EXPECT--
OK
