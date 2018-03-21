--TEST--
CommonMark\Node cached read previous
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====

Hello World
EOD
);

$f = function() use($doc) {
	return $doc->lastChild->previous;
};

$f();
$f();
echo "OK";
?>
--EXPECT--
OK
