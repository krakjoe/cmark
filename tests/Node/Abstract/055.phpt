--TEST--
CommonMark\Node isset endLine
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====
EOD
);

$title = $doc->firstChild;

$f = function() use($title) {
	return isset($title->endLine);
};

if ($f() && $f() == $f()) {
	echo "OK";
}
?>
--EXPECT--
OK
