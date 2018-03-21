--TEST--
CommonMark\Node cached read lastChild
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

$f = function() use($doc) {
	return $doc->lastChild;
};

$f();
$f();
echo "OK";
?>
--EXPECT--
OK
